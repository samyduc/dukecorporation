/**
 * A sample game.js for you to work from
 */

TheGame = pc.Game.extend('TheGame',
    { },
    {
        gameScene:null,
        menuScene:null,

        onReady:function ()
        {
            this._super();

            // disable caching when developing
            // if (pc.device.devMode)
            //    pc.device.loader.setDisableCache();

            // no resources are loaded in this template, so this is all commented out
            pc.device.loader.add(new pc.Image('room', 'images/room.png'));

            //if (pc.device.soundEnabled)
            //pc.device.loader.add(new pc.Sound('fire', 'sounds/fire', ['ogg', 'mp3'], 15));

            // fire up the loader
            pc.device.loader.start(this.onLoading.bind(this), this.onLoaded.bind(this));
            
        },

        onLoading:function (percentageComplete)
        {
            // draw title screen -- with loading bar
        },

        onLoaded:function ()
        {

            this.socket = io.connect('http://GIBSON');
            var that = this;
            this.socket.on("message",function(data){
                var response = JSON.parse(data);
                console.log("receive server message:");
                 console.log(response);
                switch(response.event){
                    case "connection":
                    
                    if(response.status){
                        that.deactivateMenu();
                        that.initGameScene(response);
                    }
                    break;
                    case "update":
                        that.updateGameScene(response);
                    break;
                    default:
                    console.log("unkonow event");
                    
                    break;
                }
            });
            // create the game scene (notice we do it here AFTER the resources are loaded)
            this.gameScene = new GameScene();
            this.addScene(this.gameScene);

            // create the menu scene (but don't make it active)
            this.menuScene = new MenuScene();
            this.addScene(this.menuScene, false);

            // resources are all ready, start the main game scene
            // (or a menu if you have one of those)
            this.activateScene(this.menuScene);
        },

        initGameScene:function(response){
            this.gameScene.initPlayerFromJSON(response);
        },

        updateGameScene:function(input_network){
            this.gameScene.onNetwork(input_network);
        },

        activateMenu:function()
        {
            $("#LoginForm").show();
            this.deactivateScene(this.gameScene);
            this.activateScene(this.menuScene);
        },

        deactivateMenu:function()
        {
            $("#LoginForm").hide();
            this.deactivateScene(this.menuScene);
            this.activateScene(this.gameScene);
        }
    });


