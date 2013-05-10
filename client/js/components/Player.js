/**
 * Player component
 */

Player = pc.components.Component('Player' ,
    {
        create:function (id, username, roomId)
        {
            var n = this._super();
            n.config(id, username, roomId);
            return n;
        }
    },
    {
        id:null,
        username:null,
        //The room the player is in
        roomId:null,
        action:null,
        dirty:false,

        init:function (id, username, action, roomId)
        {
            this._super(this.Class.shortName);
            this.config(id, username, action, roomId);
        },

        config:function (id, username, action, roomId)
        {
            this.id = id;
            this.username = username;
            this.roomId = roomId;
            this.action = action;
        },

        onNetwork: function(roomId, action){
            this.roomId = roomId;
            this.action = action;
            this.dirty = true;
        }

    });

