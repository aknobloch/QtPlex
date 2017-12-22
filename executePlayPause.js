var playButton = document.getElementsByClassName("play-btn")[0];

if(playButton && ! playButton.classList.contains("hidden"))
{
    playButton.click()
}
else
{
    document.getElementsByClassName("pause-btn")[0].click()
}

