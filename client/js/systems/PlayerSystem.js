/**
 * PlayerSystem
 */

PlayerSystem = pc.systems.EntitySystem.extend('PlayerSystem',
    {},
    {

        init:function ()
        {
            this._super([ 'player' ]);
        },

        process:function (entity)
        {
            var basicRoomComponent = entity.getComponent('player');

        }

    });