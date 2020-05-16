var keyboardEventInit = {
    'shiftKey' : true,
    'keyCode': 39,
    'which': 39
}
var rightArrowKey = new KeyboardEvent('keydown',keyboardEventInit);
document.dispatchEvent(rightArrowKey);
