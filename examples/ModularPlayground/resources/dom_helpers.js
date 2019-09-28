var getDOMPosition = function(element) {
    var top = 0, left = 0;

    var w = Number(element.offsetWidth);
    var h = Number(element.offsetHeight);

    do {
        top += element.offsetTop  || 0;
        left += element.offsetLeft || 0;
        element = element.offsetParent;
    } while(element && !element.classList.contains("Wt-domRoot"));

    var midX = left + (w / 2);
    var midY = top + (h / 2);

    return {
        top: top,
        left: left,
        midX: midX,
        midY: midY
    };
};
