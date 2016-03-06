$("#upload_avatar").ajaxSubmit({
			target: "#user_avatar",					
			url: "{% url 'upload_avatar' %}",				
			type: 'post',
			beforeSubmit: has_file,
			timeout: 2000,
			success: function (result) {
				if (result == "success") {
					$("#user_avatar").attr("src", "{% url 'user_avatar' %}?nocache="+Math.random());
					alert("图片上传成功！");
				}
				else if (result == "1M") {
					alert("图片大小不能超过1M!");
				}
				else if (result == "invalid") {
					alert("图片格式不正确!");					
				}
			}			
		});
		// not for file uploading!!!
		$.ajax({
			type: "POST",
			url:"{% url 'upload_avatar' %}",
			beforeSend: has_file,
			timeout: 3000,
			success: function(result) {
				if (result == "success") {
					$("#user_avatar").attr("src", "{% url 'user_avatar' %}?nocache="+Math.random());
					alert("图片上传成功！");
				}
				else if (result == "1M") {
					alert("图片大小不能超过1M!");
				}
				else if (result == "invalid") {
					alert("图片格式不正确!");					
				}	
				alert("lkajklfasdf");
			}
		});	
		return false;	