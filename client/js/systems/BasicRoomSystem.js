/**
 * BasicRoomSystem : all rooms have a basic room components
 */

BasicRoomSystem = pc.systems.EntitySystem.extend('BasicRoomSystem',
    {},
    {

        init:function ()
        {
            this._super([ 'RandomDeathRoom' ]);
        },

        process:function (entity)
        {
            var basicRoomComponent = entity.getComponent('BasicRoom');



        }

    });