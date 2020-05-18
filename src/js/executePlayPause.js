var mediaHandle = commonLibrary.getMediaHandle();

if(mediaHandle.paused) {

    mediaHandle.play();
}
else {

    mediaHandle.pause();
}

commonLibrary.notifySuccess();
