/**
 * BasicRoomSystem : all rooms have a basic room components
 */

BasicRoomSystem = pc.systems.EntitySystem.extend('BasicRoomSystem',
    {},
    {

        init:function ()
        {
            this._super(['BasicRoom']);
        },

        process:function (entity)
        {
            var room_component = entity.getComponent('basicroom');

            if(room_component.dirty == true) {
                room_component.dirty = false;

                var player = entity.layer.scene.player;
                player_component = player.getComponent('player');
                var room_player = player_component.getLinkedRoom();

                if(room_player != null) {
                    var room_player_component = room_player.getComponent('room_component');

                    var posTile = room_component.getTilePosition(room_player);
                    var posPx = entity.layer.scene.tileLayer.tileToScreenTile(posTile);
                    // debug
                    
                    var spatial_component = entity.getComponent('spatial');
                    spatial_component.pos.x = posPx.x;
                    spatial_component.pos.y = posPx.y;

                    var text_component = entity.getComponent('text');
                    text_component.text = ['players:'.concat(room_component.players.length.toString()), 'dead:'.concat(room_component.nb_dead.toString())];
                }
            }

        }

    });