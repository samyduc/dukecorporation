CubeTileLayer = pc.TileLayer.extend('CubeTileLayer',
    {},
    {

        px_room: null,
        nb_room: null,

        screenToTilePos: function (pos) {


            var x = pos.x;
            var y = pos.y;

            var originX = this.origin.x *-1;

            if (x < originX || x > (originX + this.nb_room * this.px_room)
                || y < this.origin.y || y > (this.origin.y + this.nb_room * this.px_room)) {
                return null;
            }

            var xFound = false;
            var yFound = false;
            for (var i = 0; i < this.nb_room; i++) {
                var startX = originX + i * this.px_room;
                var endX = originX+ (i + 1) * this.px_room;
                if (x > startX && x < endX) {
                    xFound = true;
                    break;
                }
            }

            if (!xFound) {
                return null;
            }

            for (var j = 0; j < this.nb_room; j++) {
                var startY = this.origin.y + j * this.px_room;
                var endY = this.origin.y + (j + 1) * this.px_room;
                if (y > startY && y < endY) {
                    yFound = true;
                    break;
                }
            }

            if (xFound && yFound) {
                return pc.Point.create(i, j);
            }

            return null;

        },


        tileToScreenTile: function (tilePos) {
            var x = tilePos.x  * this.px_room + (this.origin.x * -1);
            var y = tilePos.y  * this.px_room + this.origin.y;

            return pc.Point.create(x,y);
        }
    });