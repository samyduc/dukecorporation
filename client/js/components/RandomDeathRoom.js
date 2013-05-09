/**
 * RandomDeathRoom Component
 */

RandomDeathRoom = pc.components.Component('RandomDeathRoom' ,
    {
        create:function (killRate)
        {
            var n = this._super();
            n.config(killRate);
            return n;
        }
    },
    {
       killRate:0,

        init:function (killRate)
        {
            this._super(this.Class.shortName);
            this.config(killRate);
        },

        config:function (killRate)
        {
            this.killRate = killRate;
        }

    });

