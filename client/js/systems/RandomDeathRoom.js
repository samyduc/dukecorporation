/**
 * RandomDeathRoom
 */

RandomDeathRoomSystem = pc.systems.EntitySystem.extend('RandomDeathRoomSystem',
    {},
    {

        init: function () {
            this._super([ 'RandomDeathRoom' ]);
        },

        process: function (entity) {
            var randomDeathComponent = entity.getComponent('randomdeathroom');
            var basicRoomComponent = entity.getComponent('basicroom');

            var currentPlayer = entity.layer.scene.player.getComponent('player');


            basicRoomComponent.updateSurvivorsList();
            var random = Math.floor(Math.random() * 100);
            var tempPlayerList = [];
            for (var i = 0, len = basicRoomComponent.players.length; i < len; i++) {
                var isSurvivor = false;
                for (var j = 0; j < basicRoomComponent.survivors.length; j++) {
                    if (basicRoomComponent.players[i] == basicRoomComponent.survivors[j]) {
                        isSurvivor = true;
                        break;
                    }
                }
                if (!isSurvivor) {
                    if (random <= randomDeathComponent.killRate) {
                        //vote only if you are in the room
                        if (currentPlayer.roomId == basicRoomComponent.id) {
                            this.sendVoteDead(basicRoomComponent.players[i].username, basicRoomComponent);
                        }
                    } else {
                        tempPlayerList[tempPlayerList.length] = basicRoomComponent.players[i];
                        basicRoomComponent.survivors[basicRoomComponent.survivors.length] = basicRoomComponent.players[i];
                    }
                } else {
                    tempPlayerList[tempPlayerList.length] = basicRoomComponent.players[i];
                }
            }
            basicRoomComponent.players = tempPlayerList;
        },

        sendVoteDead: function (playerName, room_component) {
            var socket = pc.device.game.socket;
            var message = { event: 'vote_dead', room: room_component.id, username: playerName};
            socket.emit('message', message);
            console.log("send message:");
            console.log(message);
        }

    });