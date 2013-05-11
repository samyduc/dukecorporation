/**
 * Basic room component
 */

BasicRoom = pc.components.Component('BasicRoom',
    {
        create: function (id, playerList, nbDeadBodies, x, y) {
            var n = this._super();
            n.config(id, playerList, nbDeadBodies, x, y);
            return n;
        }
    },
    {
        id: null,
        players: null,
        survivors: null,
        nb_dead: 0,
        x: 0,
        y: 0,
        visible: false,
        dirty: true,

        init: function (id, playerList, nbDeadBodies, x, y) {
            this._super(this.Class.shortName);
            this.config(id, playerList, nbDeadBodies, x, y);
        },

        config: function (id, playerList, nbDeadBodies, x, y) {
            this.id = id;
            this.players = playerList;
            this.survivors = [];
            this.nb_dead = nbDeadBodies;
            this.x = x;
            this.y = y;
        },

        onNetwork: function (playerList, nb_dead, x, y) {
            // not reusing config
            this.players = playerList;
            this.nb_dead = nb_dead;
            this.x = x;
            this.y = y;

            this.dirty = true;
        },

        getTilePosition: function (room_center) {
            return({x: Math.abs(room_center.x - this.x - 1), y: Math.abs(room_center.y - this.y - 1)});
        },

        updateSurvivorsList: function () {
            var updatedSurvivors = [];
            for (var i = 0; i < this.survivors.length; i++) {
                var found = false;
                for (var j = 0; j < this.players.length; j++) {
                    if (this.players[j] == this.survivors[i]) {
                        found = true;
                        break;
                    }
                }
                if (found) {
                    updatedSurvivors[updatedSurvivors.length] = this.survivors[i];
                }
            }
            this.survivors = updatedSurvivors;
        }


    });

