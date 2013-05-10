/**
 *
 */


PlayerControlSystem = pc.systems.Input.extend('PlayerControlSystem',
    { },
    {

        init:function ()
        {
            this._super([ 'input' ], 60);
        },

        onAction:function (actionName, event, pos, uiTarget)
        {

            var entity = uiTarget.getEntity();


            if (actionName === 'displayPossibleActions') {
                if (entity.hasComponentOfType('basicroom')) {
                    this.createActionIcons(entity.getComponent('basicroom'));
                    this.actionicon=true;
                }
            }
            if (actionName === 'look') {
                if (entity.hasComponentOfType('basicroom')) {
                    //TODO : play effect
                    entity.getComponent('basicroom').visible = true;
                    this.actionicon=true;
                }
            }
            if (actionName === 'enter') {
               // this.player.getComponent('player').roomId = room.id;
            }


            if (actionName === 'crate pressed')
            {
                var entity = uiTarget.getEntity();

                if (entity.hasComponentOfType('spin'))
                    entity.removeComponentByType('spin');
                else
                {
                    entity.addComponent(pc.components.Spin.create({rate:10}));
                }
            }
        },

        process:function (entity)
        {
            this._super(entity);

        }
    });
