/**
 * RandomDeathRoom
 */

RandomDeathRoomSystem = pc.systems.EntitySystem.extend('RandomDeathRoom',
    {},
    {

        init:function ()
        {
            this._super([ 'RandomDeathRoom' ]);
        },

        process:function (entity)
        {
            var randomDeathComponent = entity.getComponent('RandomDeathRoom');
            var basicRoomComponent = entity.getComponent('BasicRoom');

            var random = Math.floor(Math.random()*100);
            if(random <= randomDeathComponent.killRate){
                for (var i=0,len=basicRoomComponent.playerList.length; i<len; i++)
                {
                    basicRoomComponent.playerList[i].kill();
                }
            }

        }

    });