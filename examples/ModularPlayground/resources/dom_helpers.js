var getDOMPosition = function(element) {
    var top = 0, left = 0;


    do {
        top += element.offsetTop  || 0;
        left += element.offsetLeft || 0;
        element = element.offsetParent;
    } while(element && !element.classList.contains("Wt-domRoot"));

    return {
        top: top,
        left: left
    };
};
