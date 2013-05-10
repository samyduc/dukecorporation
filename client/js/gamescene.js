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
    ZINDEX_ROOM_LAYER: 10,
    ZINDEX_PLAYER_LAYER: 20,
    ZINDEX_META_LAYER: 30
}, 
{
    roomLayer: null,
    playerLayer: null,
    metaLayer: null,
    boxes: null,
    roomSheet: null,
    isInit: false,
    player: null,
    lookAction: null,
    enterAction: null,

    init: function () {
        this._super();

        this.nb_room = 3;

        //-----------------------------------------------------------------------------
        // room layer
        //-----------------------------------------------------------------------------
        this.roomLayer = this.addLayer(new pc.EntityLayer('room layer', 10000, 10000), this.ZINDEX_META_LAYER);

        // all we need to handle the rooms
        this.roomLayer.addSystem(new BasicRoomSystem());
        this.roomLayer.addSystem(new pc.systems.Render());

        this.roomSheet = new pc.SpriteSheet({ image: pc.device.loader.get('room').resource, useRotation: false });
        this.roomSheet.alpha = 0.5;

        //-----------------------------------------------------------------------------
        // player layer
        //-----------------------------------------------------------------------------
        this.playerLayer = this.addLayer(new pc.EntityLayer('player layer', 50, 50), this.ZINDEX_PLAYER_LAYER);

        // all we need to handle the players
        this.playerLayer.addSystem(new PlayerSystem());

        // background (build default then resize)
        this.tileMap = new pc.TileMap(new pc.TileSet(this.roomSheet), this.nb_room, this.nb_room, 200, 200);
        this.tileMap.generate(0);

        this.tileLayer = this.addLayer(new CubeTileLayer('tileLayer', true, this.tileMap), this.ZINDEX_ROOM_LAYER);
        this.onResize(pc.device.canvasWidth, pc.device.canvasHeight);

        //-----------------------------------------------------------------------------
        // meta layer
        //-----------------------------------------------------------------------------
        this.uiLayer = this.addLayer(new pc.EntityLayer('uiLayer', 50, 50), this.ZINDEX_META_LAYER);
        this.uiLayer.addSystem(new pc.systems.Layout());
        this.uiLayer.addSystem(new pc.systems.Render());
        this.buildUI();
        // bind some keys/clicks/touches to access the menu

        pc.device.input.bindAction(this, 'menu', 'ESC');
        pc.device.input.bindAction(this, 'clicAction', 'MOUSE_BUTTON_LEFT_DOWN');

    },

    buildUI: function() {
        // fps counter
        this.ui_fpsCounter = pc.Entity.create(this.uiLayer);
        this.ui_fpsCounter.addComponent(pc.components.Spatial.create({ w: 200, h: 50 }));
        this.ui_fpsCounter.addComponent(pc.components.Text.create({ fontHeight: 15, lineWidth: 1, strokeColor: '#ffffff', color: '##222288', text: ['NIL'] }));
        this.ui_fpsCounter.addComponent(pc.components.Layout.create({ vertical: 'top', horizontal: 'left', margin: { left: 40, bottom: 70 }}));
        this.ui_fpsCounter.addComponent(FPSCounterComponent.create());

        // shuffle timer
        this.ui_shuffleTimer = pc.Entity.create(this.uiLayer);
        this.ui_shuffleTimer.addComponent(pc.components.Spatial.create({ w: 200, h: 50 }));
        this.ui_shuffleTimer.addComponent(pc.components.Text.create({ fontHeight: 15, lineWidth: 1, strokeColor: '#ffffff', color: '#222288', text: ['NIL'] }));
        this.ui_shuffleTimer.addComponent(pc.components.Layout.create({ vertical: 'top', horizontal: 'left', margin: { left: 40, bottom: 70 }}));
        this.ui_shuffleTimer.addComponent(TimerComponent.create(0, 0));

        this.uiLayer.addSystem(new TimerSystem());
        this.uiLayer.addSystem(new FPSCounterSystem());
    },

    // handle menu actions
    onAction: function (actionName, event, pos, uiTarget) {
        if (pc.device.game.menuScene.active)
            return true;

        var room = null;
        if (uiTarget != null) {
            var roomEntity = uiTarget.getEntity() ;
               room = roomEntity.getComponent('basicroom');
        }
        if (actionName === 'menu')
            pc.device.game.activateMenu();
        if (actionName === 'clicAction') {
            var roomCoordinates = this.tileLayer.screenToTilePos(pos);
            this.createActionIcons(room);
        }


        return false; // eat the event (so it wont pass through to the newly activated menuscene
    },

    process: function () {

        //if (!pc.device.loader.finished) return;
        // clear the background
        pc.device.ctx.clearRect(0, 0, pc.device.canvasWidth, pc.device.canvasHeight);

        // always call the super
        this._super();
    },
    initPlayerFromJSON:function (reponse) {
        this.player = pc.Entity.create(this.playerLayer);
        this.player.addComponent(Player.create(reponse.id, reponse.username, reponse.action, reponse.room));
    },

    update: function (rooms) {
        if (this.isInit) {

        } else {
            this.initMap(rooms);
            this.isInit = true;
        }
    },

    onNetworkPlayerUpdate: function(network_update) {

        var player_component = this.player.getComponent('player');
        player_component.onNetwork(network_update.action, network_update.room);
    },

    onNetworkRoomUpdate: function(network_rooms) {
        var roomList = network_rooms;

        for (var i = 0; i < roomList.length; i++) {
            var network_room = roomList[i];
            
            var temp_room = this.getRoomById(network_room.id);

            if(temp_room != null) {
                // update
                basic_component = temp_room.getComponent('basicroom');
                basic_component.onNetwork(network_room.players, network_room.dead_nb, network_room.x, network_room.y)
            }
            else {
                this.createRoom(network_room);
            }
        }
    },

    onNetwork: function(input_network) {

        if(this.player == null) {
            return;
        }

        var timer_component = this.ui_shuffleTimer.getComponent("timercomponent");
        timer_component.config(input_network.shuffle_start, input_network.shuffle_duration);

        if(input_network.event == 'update'){
            // sync local data with new
            this.onNetworkPlayerUpdate(input_network);
            this.onNetworkRoomUpdate(input_network.rooms);
        }
    },

    createRoom: function (network_room) {
        var room = pc.Entity.create(this.roomLayer);
        room.addComponent(BasicRoom.create(network_room.id, network_room.players, network_room.dead_nb, network_room.x, network_room.y));
        room.addComponent(pc.components.Spatial.create({ w: 200, h: 50 }));
        //room.addComponent(pc.components.Layout.create({ vertical: 'middle', horizontal: 'right', margin: { left: 240, bottom: 70 }}));
        room.addComponent(pc.components.Text.create({ fontHeight: 20, lineWidth: 2, strokeColor: '#ff9800', color: '#ff9800', text: ['NIL'] }));
        switch (network_room.type) {
            case this.ROOM_RANDOM_DEATH:
                room.addComponent(RandomDeathRoom.create({killRate: Math.floor((Math.random()*100)) }));
                break;
            case this.ROOM_DEATH:
                room.addComponent(RandomDeathRoom.create({killRate: 100}));
                break;
            default:
                break;
        }
    },

    createActionIcons: function (room) {
        //var player = this.player.getComponent('player');
        //if(player != null && !this.player.rooms.contains(room.id)){
        this.lookAction = pc.Entity.create(this.uiLayer);
        this.lookAction.addComponent(pc.components.Spatial.create({ x: 200, y: 200, w: 89, h: 75 }));
        this.lookAction.addComponent(pc.components.Rect.create({ color: [ pc.Math.rand(0, 255), pc.Math.rand(0, 255), pc.Math.rand(0, 255) ] }));
        this.lookAction.addComponent(pc.components.Text.create({ fontHeight: 25, text: ['<=>'], offset: { x:15, y:-10 } }));

        pc.device.input.bindAction(this, 'look', 'MOUSE_BUTTON_LEFT_DOWN', this.lookAction.getComponent("spatial"));
        //  }
        // if(player.roomId != room.id){
        this.enterAction = pc.Entity.create(this.uiLayer);
        this.enterAction.addComponent(pc.components.Spatial.create({ x: 500, y: 200, w: 75, h: 75 }));
        this.enterAction.addComponent(pc.components.Rect.create({ color: [ pc.Math.rand(0, 255), pc.Math.rand(0, 255), pc.Math.rand(0, 255) ] }));
        this.enterAction.addComponent(pc.components.Text.create({ fontHeight: 25, text: ['|\'|'], offset: { x:15, y:-10 } }));
        pc.device.input.bindAction(this, 'enter', 'MOUSE_BUTTON_LEFT_DOWN', this.enterAction.getComponent("spatial"));
        //  }
    },

    onResize: function(width, height) {
        
        var px_room = 0;
        var ratio = 0;
        var center_x = 0;
        var center_y = 0;
        // compute better ratio
        if(width > height) {
            ratio = height;
        }
        else {
            ratio = height;
        }

        px_room = Math.floor(ratio / this.nb_room);

        var scale = px_room / this.roomSheet.frameWidth;

        this.roomSheet.setScale(scale, scale);

        this.tileMap.tileWidth = px_room;
        this.tileMap.tileHeight = px_room;

        if(width > height) {
            center_x = -1*(width/2 - px_room*this.nb_room/2);
        }
        else {
            center_y = -1*(height/2 - px_room*this.nb_room/2);
        }          

        this.tileLayer.setOrigin(center_x, center_y);
        this.tileLayer.px_room = px_room;
        this.tileLayer.nb_room = this.nb_room;
        this.tileLayer.prerender();
    },

    getRoomById: function(id){
        var room = null;

        var list_entities = this.roomLayer.entityManager.entities;
        var node = list_entities.first;

        while(node) {
            var room_component = node.object().getComponent('basicroom');

            if(room_component.id == id){
                room = node.object();
                break;
            }

            node = node.next();
        }

        return room;
    },

    tileToWorldRoom: function(tilePos, player){
        var list_entities = this.roomLayer.entityManager.entities;
        var pos = pc.Point.create(-1, -1);
        var node = list_entities.first;
        var player_component = player.getComponent('player');

        var room_temp = this.getRoomById(player_component.roomId);
        if(room_temp == null) {
            return pos;
        }

        var room_center_component = room_temp.getComponent('basicroom');

        while(node) {
            room_component = node.object().getComponent('basicroom');
            tiled_pos = room_component.getTilePosition(room_center_component);

            if(tiled_pos.x == tilePos.x && tiled_pos.y == tilePos.y){
                pos.x = room_component.x;
                pos.y = room_component.y;
                break;
            }

            node = node.next();
        }

        return pos;
    }
 
});
