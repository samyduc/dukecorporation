/**
 * GameScene
 * A template game scene
 */
GameScene = pc.Scene.extend('GameScene',
    {
        ROOM_POISON: 1, // le second qui rentre tue le premier
        ROOM_FLOOD: 2, // 5s pour sortir de la salle
        ROOM_DEATH: 3, //rentrer signifie la mort
        ROOM_RANDOM_DEATH: 4, // pourcentage de chance de mourir
        ROOM_SAFE: 5, // totalemetn sans danger
        ROOM_TELEPORT: 6, // teleporte vers une autre salle du meme type
        ROOM_PRISON: 7, // bloque pendant un certain cooldown
        ROOM_SPAWN: 8, // spawn de depart
        ROOM_EXIT: 9, //salle de sortie

        //Layer's zIndex
        ZINDEX_ROOM_LAYER:1,
        ZINDEX_PLAYER_LAYER:2
    },
    {
        roomLayer: null,
        playerLayer:null,
        boxes: null,
        roomSheet: null,
        isInit:false,
        init: function () {
            this._super();

            this.boxes = [];

            //-----------------------------------------------------------------------------
            // room layer
            //-----------------------------------------------------------------------------
            this.roomLayer = this.addLayer(new pc.EntityLayer('room layer', 10000, 10000), this.ZINDEX_ROOM_LAYER);

            // all we need to handle the rooms
            this.roomLayer.addSystem(new BasicRoomSystem());
            this.roomLayer.addSystem(new RandomDeathRoomSystem());
            this.roomLayer.addSystem(new pc.systems.Render());
            //-----------------------------------------------------------------------------
            // player layer
            //-----------------------------------------------------------------------------
            this.playerLayer = this.addLayer(new pc.EntityLayer('player layer', 10000, 10000), this.ZINDEX_PLAYER_LAYER);

            // all we need to handle the players
            this.playerLayer.addSystem(new PlayerSystem());
            this.roomSheet = new pc.SpriteSheet({ image:pc.device.loader.get('room').resource, useRotation:false });
            // bind some keys/clicks/touches to access the menu
            pc.device.input.bindAction(this, 'menu', 'ENTER');
            pc.device.input.bindAction(this, 'menu', 'ESC');
            pc.device.input.bindAction(this, 'menu', 'MOUSE_BUTTON_LEFT_DOWN');
            pc.device.input.bindAction(this, 'menu', 'TOUCH');

        },

        // handle menu actions
        onAction: function (actionName, event, pos, uiTarget) {
            if (pc.device.game.menuScene.active)
                return true;

            if (actionName === 'menu')
                pc.device.game.activateMenu();

            return false; // eat the event (so it wont pass through to the newly activated menuscene
        },

        process: function () {
            // clear the background
            pc.device.ctx.clearRect(0, 0, pc.device.canvasWidth, pc.device.canvasHeight);

            // always call the super
            this._super();

            //
            // ... do extra processing in here
            //
        },

        update:function(rooms){
            if(this.isInit){

            } else {
                this.initMap(rooms);
                this.isInit=true;
            }
        },

        initMap: function (roomList) {
            for (var i = 0; i < roomList.length; i++) {
                var jsonRoom = roomList[i];
                this.createRoom(jsonRoom);
            }
        },

        createRoom: function (jsonRoom) {
            var room = pc.Entity.create(this.roomLayer);
            room.addComponent(BasicRoom.create({ id: jsonRoom.id, playerList: jsonRoom.players, deadBodies: jsonRoom.dead_nb, x: jsonRoom.x, y: jsonRoom.y}));
            var roomSprite = pc.components.Sprite.create({ spriteSheet:this.roomSheet});
            room.addComponent(roomSprite);
            room.addComponent(pc.components.Spatial.create({x:100+jsonRoom.x*this.roomSheet.frameWidth, y:100+jsonRoom.y*this.roomSheet.frameHeight, dir:0,
                        w:this.roomSheet.frameWidth, h:this.roomSheet.frameHeight}));
            switch (jsonRoom.type) {
                case this.ROOM_RANDOM_DEATH:
                    room.addComponent(RandomDeathRoom.create({killRate: jsonRoom.killRate}));
                    break;
                case this.ROOM_DEATH:
                    room.addComponent(RandomDeathRoom.create({killRate: 100}));
                    break;
                default:
                    break;
            }
        }
    });
