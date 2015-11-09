// JavaScript Document
$(document).ready(function(e){
    $("button").click(function(){
		// iterate every img to resize the width.
		/*$("img").each(function(){
			if($(this).width() > $(this).parent().width()) {
		$(this).width('100%');
	}
		});
		*/
		$(this).animate({
			marginLeft: '0',
			marginTop: '10%',
			width: '0',
			height: '0',
			fontSize: '0'
		}, 'slow', callback=function(){
			$(this).fadeOut(800, callback=function(){
				window.location.href="http://google.com";
			})
		});
	})
	/* from .. to ..
	var hoverTime = 1;
	.mouseenter(function(){
		if(hoverTime == 1){
			$(this).animate({
				width: '110%'
			}, 1000);
			hoverTime -= 1;
		}
	})
	*/
	/* need some time to rotate!
	.mouseenter(function(){
		$(this).css('width', function(value){
			return value + '30%';
		});
	*/
	// sometimes, need to use css rather than attr.
	// value = 0?
	.mouseenter(function(){
		$("#arrow").css('width', function(value){
			return value + '16%';
		}).css('z-index', '-7');
	})
	.mouseleave(function(){
		$("#arrow").css('width', '13%').css('z-index', '-2');
		//$(this).show(500); 
		//may be it is not useful at present.
	})
});
