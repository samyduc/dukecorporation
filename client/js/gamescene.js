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
        ZINDEX_ROOM_LAYER: 1,
        ZINDEX_PLAYER_LAYER: 2,
        ZINDEX_META_LAYER: 3
    },
    {
        roomLayer: null,
        playerLayer: null,
        metaLayer:null,
        boxes: null,
        roomSheet: null,
        player: null,

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
            this.roomSheet = new pc.SpriteSheet({ image: pc.device.loader.get('room').resource, useRotation: false });

            //-----------------------------------------------------------------------------
            // player layer
            //-----------------------------------------------------------------------------
            this.playerLayer = this.addLayer(new pc.EntityLayer('player layer', 10000, 10000), this.ZINDEX_PLAYER_LAYER);

            // all we need to handle the players
            this.playerLayer.addSystem(new PlayerSystem());

            //-----------------------------------------------------------------------------
            // meta layer
            //-----------------------------------------------------------------------------
            this.metaLayer = this.addLayer(new pc.EntityLayer('meta layer', 10000, 10000), this.ZINDEX_META_LAYER);

            // all we need to handle the players
            this.metaLayer.addSystem(new pc.System.Render());


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

            var room = uiTarget.getEntity().getComponent('BasicRoom');

            if (actionName === 'menu')
                pc.device.game.activateMenu();
            if (actionName === 'displayPossibleActions'){
               this.createActionIcons(room);
            }
            if (actionName === 'look'){
                this.player.getComponent('player').rooms[this.player.rooms.length] = room.id;
            }
            if (actionName === 'enter'){
                this.player.getComponent('player').roomId = room.id;
             }

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

        initMap:function (rooms) {
            var roomList = JSON.parse(rooms);
            for (var i = 0; i < roomList.count; i++) {
                var jsonRoom = roomList[i];
                this.createRoom(jsonRoom);
            }
        },

        createRoom: function (jsonRoom) {
            var room = pc.Entity.create(this.roomLayer);
            room.addComponent(BasicRoom.Create({ id: jsonRoom.id, playerList: jsonRoom.players, deadBodies: jsonRoom.dead_nb, x: jsonRoom.x, y: jsonRoom.y}));
            room.addComponent(pc.components.Sprite.create({ spriteSheet: this.roomSheet}));
            switch (jsonRoom.type) {
                case this.ROOM_RANDOM_DEATH:
                    room.addComponent(RandomDeathRoom.Create({killRate: jsonRoom.killRate}));
                    break;
                case this.ROOM_DEATH:
                    room.addComponent(RandomDeathRoom.Create({killRate: 100}));
                    break;
                default:
                    break;
            }
            pc.device.input.bindAction(this, 'displayPossibleActions', 'MOUSE_BUTTON_LEFT_DOWN', room.getComponent('spatial') );
        },

        createActionIcons: function(room){
            var player = this.player.getComponent('player');
            if(player != null && !this.player.rooms.contains(room.id)){
                var lookAction = pc.Entity.create(this.metaLayer);
                lookAction.addComponent(pc.components.Spatial.create({ x:200, y:200, w:75, h:75 }));
                lookAction.addComponent(pc.components.Rect.create({ color:[ pc.Math.rand(0, 255), pc.Math.rand(0, 255), pc.Math.rand(0, 255) ] }));
                pc.device.input.bindAction(this, 'look', 'MOUSE_BUTTON_LEFT_DOWN', lookAction.getComponents("spatial"));
            }
            if(player.roomId != room.id){
                var enterAction = pc.Entity.create(this.metaLayer)   ;
                enterAction.addComponent(pc.components.Spatial.create({ x:200, y:200, w:75, h:75 }));
                enterAction.addComponent(pc.components.Rect.create({ color:[ pc.Math.rand(0, 255), pc.Math.rand(0, 255), pc.Math.rand(0, 255) ] }));
                pc.device.input.bindAction(this, 'enter', 'MOUSE_BUTTON_LEFT_DOWN', enterAction.getComponents("spatial"));
            }
        }

    });
