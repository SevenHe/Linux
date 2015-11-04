# Every group has a group name,and some members which can be added into the group,
# And every group has a level-down group array.
# Emulate a member as a str.

class Group:
	
	def __init__(self, name, lower_groups=[]):
		self.group_name = name;
		self.lower_groups = lower_groups;
		self.members = []
		
	# Could be expanded into add a list of members.
	def addMember(self, member):
		self.members.append(member)
		
	def addGroup(self, group):
		if isinstance(group, Group):
			self.lower_groups.append(group)
		else:
			print("Parameter is invalid, should a Group.")

	def getMembers(self):
		print(self.members)
		return self.members
		
	def getGroups(self):
		names = [ x.getName() for x in self.lower_groups]
		print(names)
		return self.lower_groups
		
	def getName(self):
		return self.group_name
		

if __name__ == "__main__":
	print("Program test has been started!")
	root_group = Group('groupR')
	n_group = Group('groupN')
	m_group = Group('groupM')
	root_group.addGroup(n_group)
	root_group.addGroup(m_group)
	root_group.addMember('Bobe')
	assert root_group.getMembers()[0] == 'Bobe', MemberError
	assert isinstance(root_group.getGroups()[0], Group), TypeError
	print("If there is no error now, so test is finished.")
	 
	