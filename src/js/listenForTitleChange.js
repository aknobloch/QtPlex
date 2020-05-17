// (function findTitle() {
    
    
//     var titleChanged = false;
//     var maxWaitAttempts = 1000;
//     var currentWaitAttempts = 0;

//     // listen for the next title change event
//     document.getElementsByTagName("audio")[0]
//         .addEventListener("play", function() { 
//             titleChanged = true;
//         })

//     while(currentWaitAttempts < maxWaitAttempts && ! titleChanged) {

//         maxWaitAttempts++;
//     }

//     if(titleChanged == false) {
//         return "Error Finding Song."
//     }
//     else {
//         return document.title;
//     }
// })();
document.title