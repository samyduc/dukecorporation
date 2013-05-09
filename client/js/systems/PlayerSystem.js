/**
 * PlayerSystem
 */

PlayerSystem = pc.systems.EntitySystem.extend('PlayerSystem',
    {},
    {

        init:function ()
        {
            this._super([ 'PlayerSystem' ]);
        },

        process:function (entity)
        {
            var basicRoomComponent = entity.getComponent('Player');

        }

    });