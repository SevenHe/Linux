from django import forms

class ContactForm(forms.Form):
	# can add a parameter as 'widget=forms.Textarea'.
	# also can set 'max_length=?'
	# and custom tag:label='?'
	# and in the view processer, we can "form = ContactForm(initial={'subject': 'I love your site!'})" as a default value.
    subject = forms.CharField()
	email = forms.EmailField(required=False)
	message = forms.CharField()

	# another check by myself, must start with clean_ to be called automatically
	def clean_message(self):
        message = self.cleaned_data['message']
        num_words = len(message.split())
        if num_words < 4:
            raise forms.ValidationError("Not enough words!")
        return message
