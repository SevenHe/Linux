from django import forms

class AvatarUploadForm(forms.Form):
    """
    upload user avatar!
    """
    avatar = forms.ImageField()
