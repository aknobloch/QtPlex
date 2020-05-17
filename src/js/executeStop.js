// TODO (#9) - detect if we are already stopped, and don't resume if so
var spaceKey = new KeyboardEvent('keydown',{'keyCode':32,'which':32});
document.dispatchEvent(spaceKey);
