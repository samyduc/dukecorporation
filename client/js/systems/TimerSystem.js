


TimerSystem = pc.systems.EntitySystem.extend('TimerSystem',
    {},
    {

        init:function ()
        {
            this._super(['TimerComponent']);
        },

        process:function (entity)
        {
            var timer_component = entity.getComponent('TimerComponent');

            if(timer_component != null) {
                var text_component = entity.getComponent('text');
                text_component.text = [timer_component.getTimeLeft().toString()];
            }
        }

    });