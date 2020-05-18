// Provides a singleton common library so that all our files
// don't have to repeat code. This is loaded and executed by 
// the PlexWebPage class on initialization.
class CommonLibrary {

    // When called, emits true to allow the 
    // PlexWebPage to respond appropriately.
    notifySuccess() {
        return true;
    }

    logInfo(message) {
        console.log("[QtPlex] " + message);
    }

    logError(message) {
        console.error("[QtPlex] " + message);
    }

    getMediaHandle() {

        var playingMedia = document.getElementsByTagName('audio');
    
        // Audio not found, check for playing video
        if(playingMedia.length === 0) {
    
            playingMedia = document.getElementsByTagName('video');
        }
    
        if(playingMedia.length === 0) {
    
            this.logInfo("Could not find media playback tag.");
            return undefined;
        }
    
        if(playingMedia.length > 1) {

            this.logError("Unknown state! Multiple media sources found, aborting.");
            return undefined;
        }
    
        return playingMedia[0];
    }
}

var commonLibrary = new CommonLibrary();
commonLibrary.notifySuccess();
