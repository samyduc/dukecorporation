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
        }

    });

