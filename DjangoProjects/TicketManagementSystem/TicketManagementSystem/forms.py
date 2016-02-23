# -*- encoding: utf-8 -*-
from django import forms

class LogInForm(forms.Form):
    username = forms.CharField(max_length=15, error_messages={'required':u'*不可为空'})
    email = forms.EmailField(error_messages={'required':u'*不可为空'})
    password = forms.CharField(max_length=16, widget=forms.PasswordInput, error_messages={'required':u'*不可为空'})
    repassword = forms.CharField(max_length=16, widget=forms.PasswordInput, error_messages={'required':u'*不可为空'})
    diag_input = forms.CharField(max_length=4, error_messages={'required':u'*不可为空'})


    def clean_repassword(self):
        repswd = self.cleaned_data['repassword']
        pswd = self.cleaned_data['password']
        if pswd != repswd:
            self.add_error('repassword', u'*两次密码不一致！')

        # Always return it!
        return repswd

