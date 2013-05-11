/**
 * RandomDeathRoom
 */

RandomDeathRoomSystem = pc.systems.EntitySystem.extend('RandomDeathRoomSystem',
    {},
    {

        init:function ()
        {
            this._super([ 'RandomDeathRoomSystem' ]);
        },

        process:function (entity)
        {
            var randomDeathComponent = entity.getComponent('RandomDeathRoom');
            var basicRoomComponent = entity.getComponent('BasicRoom');

            var random = Math.floor(Math.random()*100);
            if(random <= randomDeathComponent.killRate){
                for (var i=0,len=basicRoomComponent.playerList.length; i<len; i++)
                {
                  this.sendVoteDead(basicRoomComponent.playerList[i]);
                }
            }

        },

        sendVoteDead: function (playerName, room_component) {
            var socket = pc.device.game.socket;
            socket.emit('message', { event: 'vote_dead', room: room_component.id, username: playerName});
        }

    });