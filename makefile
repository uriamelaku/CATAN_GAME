# ה-GCC הוא הקומפיילר שנשתמש בו
CXX = g++
CXXFLAGS = -Wall -std=c++17

# רשימת כל קבצי המקור
SRCS = Main.cpp Board.cpp HexTile.cpp Corner.cpp Edge.cpp Player.cpp DevelopmentCard.cpp DevelopmentCardDeck.cpp

# יצירת רשימת קבצי האובייקט מקבצי המקור
OBJS = $(SRCS:.cpp=.o)

# שם קובץ ההפעלה
EXEC = Main

# ברירת מחדל: קמפל והפוך את כל קבצי המקור לתוכנית בינארית
all: $(EXEC)

# חוק כללי להמרת קבצי מקור לקבצי אובייקט
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# חיבור כל קבצי האובייקט לקובץ הפעלה
$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(EXEC)

# ניקוי קבצים שנוצרו
clean:
	rm -f $(OBJS) $(EXEC)
