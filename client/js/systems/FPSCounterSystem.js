


FPSCounterSystem = pc.systems.EntitySystem.extend('FPSCounterSystem',
    {},
    {

        init:function ()
        {
            this._super(['FPSCounterComponent']);
        },

        process:function (entity)
        {
            var text_component = entity.getComponent("text");
            text_component.text = [pc.device.currentFPS.toString()];
        }

    });