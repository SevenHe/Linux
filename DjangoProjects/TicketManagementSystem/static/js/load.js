// just render the template, not for .js file!
$(document).ready(function () {
	$("input[name='avatar']").hide();
	$("#submit_avatar").click(function() {
		$("input[name='avatar']").click();
	});
	$("#upload_avatar").submit(function (result) {
		$("#upload_avatar").ajaxSubmit({
				type: 'post',
				url: "{% url 'upload_avatar' %}",
				success: function (result) {
					if (result == "success") {
						$("#user_avatar").attr("src", "{% url 'user_avatar' %}?nocache="+Math.random());
					}
					else if (result == "1M") {
						alert("图片大小不能超过1M!");
					}
					else if (result == "invalid") {
						alert("图片格式不正确!");					
					}
				}			
		});	
		return false;
	});
});