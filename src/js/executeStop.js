function stopIfPlaying(mediaHandle) {

    if(mediaHandle == null) {
        return;
    }

    if(mediaHandle.paused) {

        commonLibrary.logInfo("Media is already stopped.");
        return;
    }

    mediaHandle.pause();
}

var mediaHandle = commonLibrary.getMediaHandle();
stopIfPlaying(mediaHandle);

commonLibrary.notifySuccess();
