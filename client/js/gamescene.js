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
        ROOM_EXIT: 9 //salle de sortie
    },
    {
        gameLayer: null,
        boxes: null,

        init: function () {
            this._super();

            this.boxes = [];

            //-----------------------------------------------------------------------------
            // game layer
            //-----------------------------------------------------------------------------
            this.gameLayer = this.addLayer(new pc.EntityLayer('game layer', 10000, 10000));

            // all we need is the render and effects systems
            this.gameLayer.addSystem(new pc.systems.Render());
            this.gameLayer.addSystem(new pc.systems.Effects());
            this.gameLayer.addSystem(new BasicRoomSystem());
            this.gameLayer.addSystem(new RandomDeathRoomSystem());

            for (var i = 0; i < 3; i++) {
                var box = pc.Entity.create(this.gameLayer);
                box.addComponent(pc.components.Spatial.create({ x: 200 + (i * 100), y: 200, w: 75, h: 75 }));
                box.addComponent(pc.components.Rect.create({ color: [ pc.Math.rand(0, 255), pc.Math.rand(0, 255), pc.Math.rand(0, 255) ] }));

                this.boxes.push(box);
            }

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

        initMap: function (rooms) {
            var roomList = JSON.parse(rooms);
            for (var i = 0; i < roomList.count; i++) {
                var jsonRoom = roomList[i];
                createRoom(jsonRoom);
            }
        },

        createRoom: function (jsonRoom) {
            var room = pc.Entity.create(this.gameLayer);
            room.addComponent(BasicRoom.Create({ id: jsonRoom.id, playerList: jsonRoom.players, deadBodies: jsonRoom.dead_nb, x: jsonRoom.x, y: jsonRoom.y}));
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
        }
    });
