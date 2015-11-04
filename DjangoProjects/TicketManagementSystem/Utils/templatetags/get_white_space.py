from django import template

register = template.Library()

# take care of the indentation!
@register.tag
def get_white_space(parser, token):
	try:
		tag_name, arg = token.contents.split(None, 1);
	except ValueError:
		msg = '%r tag requires arguments' % token.contents[0]
		raise template.TemplateSyntaxError(msg)
	return WhiteSpaceNode(arg)

class WhiteSpaceNode(template.Node):
	def __init__(self, arg):
		self.arg = int(arg)

	def render(self, context):
		spaces = ""
		while self.arg > 0:
			spaces += "&nbsp;"
			self.arg -= 1
		return spaces
