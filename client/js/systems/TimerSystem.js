


TimerSystem = pc.systems.EntitySystem.extend('TimerSystem',
    {},
    {

        init:function ()
        {
            this._super(['TimerComponent']);
        },

        process:function (entity)
        {
            var timer_component = entity.getComponent('timercomponent');

            var text_component = entity.getComponent('text');
            text_component.text = [Math.ceil(timer_component.getTimeLeft()).toString()];
        }

    });