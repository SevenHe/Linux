# -*- encoding: utf-8 -*-
from django import forms

class LogInForm(forms.Form):
    username = forms.CharField(max_length=15, error_messages={'required':u'用户名不能为空'})
    email = forms.EmailField(error_messages={'required':u'邮箱不能为空'})
    password = forms.CharField(max_length=16, widget=forms.PasswordInput, error_messages={'required':u'密码不能为空'})
    repassword = forms.CharField(max_length=16, widget=forms.PasswordInput, error_messages={'required':u'二次密码不能为空'})
    diag_input = forms.CharField(max_length=4, error_messages={'required':u'验证码不能为空'})

    def clean_email(self):
        email = self.cleaned_data['email']
        import re
        raise forms.ValidationError('stop operation!')
        return email

    def clean_repassword(self):
        repswd = self.cleaned_data['repassword']
        pswd = self.cleaned_data['password']
        if pswd != repswd:
            raise forms.ValidationError("两次密码输入不一致！")
        return repswd

    def captcha_error(self):
        raise forms.ValidationError("验证码错误！")

