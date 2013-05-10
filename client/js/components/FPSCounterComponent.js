
FPSCounterComponent = pc.components.Component('FPSCounterComponent' ,
    {
        create:function ()
        {
            var n = this._super();
            n.config();
            return n;
        }
    },
    {
        init:function ()
        {
            this._super(this.Class.shortName);
            this.config();
        },

        config:function ()
        {
        },
    });

