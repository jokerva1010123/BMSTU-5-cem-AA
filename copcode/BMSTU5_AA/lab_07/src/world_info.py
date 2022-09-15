class WorldInfo(object):
	founder = str()
	year_of_issue = int()
	genre = str()
	age_restrictions = int()
	price = int()

	def __init__(self, founder, year_of_issue, genre, age_restrictions, price):
		self.founder = founder
		self.year_of_issue = year_of_issue
		self.genre = genre
		self.age_restrictions = age_restrictions
		if price > 0:
			self.price = price

	def __str__(self):
		return "founder: {0}\nyear_of_issue: {1}\n\
genre: {2}\nage_restrictions: {3}\n\
price: {4}\n".format(self.founder,
		self.year_of_issue, self.genre,
		self.age_restrictions, self.price)
