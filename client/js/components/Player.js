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
        //The rooms the player can see
        rooms:null,

        init:function (id, username, roomId)
        {
            this._super(this.Class.shortName);
            this.config(id, username, roomId);
        },

        config:function (id, username, roomId)
        {
            this.id = id;
            this.username = username;
            this.roomId = roomId;
            this.rooms = [];
        }

    });

