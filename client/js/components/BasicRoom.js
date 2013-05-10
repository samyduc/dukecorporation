/**
 * Basic room component
 */

BasicRoom = pc.components.Component('BasicRoom' ,
    {
        create:function (id, playerList, nbDeadBodies, x, y)
        {
            var n = this._super();
            n.config(id, playerList, nbDeadBodies, x, y);
            return n;
        }
    },
    {
        id:null,
        playerList:null,
        nbDeadBodies:0,
        x:0,
        y:0,
        visible:false,

        init:function (id, playerList, nbDeadBodies, x, y)
        {
            this._super(this.Class.shortName);
            this.config(id, playerList, nbDeadBodies, x, y);
        },

        config:function (id, playerList, nbDeadBodies, x, y)
        {
            this.id = id;
            this.playerList = playerList;
            this.nbDeadBodies = nbDeadBodies;
            this.x = x;
            this.y = y;
        },

        createActionIcons: function () {
            //var player = this.player.getComponent('player');
            //if(player != null && !this.player.rooms.contains(room.id)){
            this.lookAction = pc.Entity.create(this.layer);
            this.lookAction.addComponent(pc.components.Spatial.create({ x: 200, y: 200, w: 89, h: 75 }));
            this.lookAction.addComponent(pc.components.Rect.create({ color: [ pc.Math.rand(0, 255), pc.Math.rand(0, 255), pc.Math.rand(0, 255) ] }));
            this.lookAction.addComponent(pc.components.Text.create({ fontHeight: 25, text: ['<=>'], offset: { x: 15, y: -10 } }));
            this.lookAction.addComponent(pc.components.Input.create({actions: [['look', ['MOUSE_BUTTON_LEFT_DOWN']]],   }));
            //  }
            // if(player.roomId != room.id){
            this.enterAction = pc.Entity.create(this.layer);
            this.enterAction.addComponent(pc.components.Spatial.create({ x: 500, y: 200, w: 75, h: 75 }));
            this.enterAction.addComponent(pc.components.Rect.create({ color: [ pc.Math.rand(0, 255), pc.Math.rand(0, 255), pc.Math.rand(0, 255) ] }));
            this.enterAction.addComponent(pc.components.Text.create({ fontHeight: 25, text: ['|\'|'], offset: { x: 15, y: -10 } }));
            this.enterAction.addComponent(pc.components.Input.create({ actions: [['enter', ['MOUSE_BUTTON_LEFT_DOWN']]], target : room  }));
        }

    });

