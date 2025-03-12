# Author : Lily Zhen
# GitHub Username : lilyzhen2
# Date : 12/05/2024
# Description : Defines three classes: Movie, StreamingService, and StreamingGuide. Movie creates objects with four data
# members: title, genre, director, and year. StreamingService creates dictionaries with Movie titles as keys and
# Movie objects as values. Movies can be added and removed from StreamingService. StreamingGuide creates lists of
# StreamingServices. StreamingServices can be added and removed from StreamingGuide. StreamingGuide also contains a
# method that takes a movie title as a parameter and returns a dictionary with movie title, movie year, and streaming
# services that show the movie, or None if the movie is not available on any StreamingServices.

# class Movie with data members title, genre, director, and year
class Movie:
    """ Represents a movie with a title, genre, director name, and year. """
    # initialize method with title, genre, director, and year as arguments in that order
    def __init__(self, title, genre, director, year):
        """ Creates a Movie with a title, genre, director, and year. """

        # year is integer, rest of arguments are strings
        self._title = str(title)
        self._genre = str(genre)
        self._director = str(director)
        self._year = int(year)

    # get methods for each data member
    def get_title(self):
        """ Returns Movie title. """

        return self._title

    def get_genre(self):
        """ Returns Movie genre. """

        return self._genre

    def get_director(self):
        """ Returns Movie director. """

        return self._director

    def get_year(self):
        """ Returns Movie year. """

        return self._year

# class StreamingService with data members name and catalog
class StreamingService:
    """ Creates a StreamingService that has a name and a dictionary of Movies, with titles as keys and Movie objects as values. """

    # initialize method that assigns name to name data member, catalog data member to empty dictionary
    # catalog is a dictionary of Movies, keys are titles of Movie objects, values are Movie objects, name is string
    def __init__(self, name):
        """ Creates a StreamingService with a name and catalog that is a dictionary. """

        self._name = str(name)
        self._catalog = {}

    # get methods for name and catalog
    def get_name(self):
        """ Returns StreamingService name. """

        return self._name

    def get_catalog(self):
        """ Returns StreamingService catalog. """

        return self._catalog

    # method add_movie that takes Movie object as argument and adds to catalog dictionary
    # key should be movie title, value should be Movie object
    def add_movie(self, movie_obj):
        """ Adds Movie object to catalog. """

        self._catalog[Movie.get_title(movie_obj)] = movie_obj

    # method delete_movie that takes Movie title as argument and if in catalog, removes it
    def delete_movie(self, movie_title):
        """ Removes movie from catalog. """

        if movie_title in self._catalog:
            self._catalog.pop(movie_title)

# class StreamingGuide with data member that is a list of StreamingService objects
class StreamingGuide:
    """ Creates a StreamingGuide that takes a list of StreamingServices as its parameter and returns
    a dictionary containing the title, year, and available streaming service of a movie. """

    # initialize method that takes no arguments and assigns data member to empty list
    def __init__(self):
        """ Assigns StreamingGuide to an empty list. """

        self._list_services = []

    # method add_streaming_service that takes a StreamingService object as argument and adds to the list
    def add_streaming_service(self, service_obj):
        """ Takes a StreamingService object as parameter and adds it to StreamingGuide list. """

        self._list_services.append(service_obj)

    # method delete_streaming_service that takes the name of a streaming service as argument and if in list, removes it
    def delete_streaming_service(self, service_name):
        """ If name of StreamingService in list, removes StreamingService from StreamingGuide list. """

        # iterate over service objects list
        for service_obj in self._list_services:
            # if parameter is the name of streaming service, remove service from list
            if service_name is StreamingService.get_name(service_obj):
                self._list_services.remove(service_obj)

    # method who_streams_this_movie that takes movie title as parameter and returns either a dictionary or value None
    # dictionary should contain 3-key value pairs :
    # keys title, year, and services
    # value title should be title of the movie (which was passed to this function as a parameter)
    # value year should be year of the movie (as an integer)
    # value services should be list of the names of streaming services showing that movie
    def who_streams_this_movie(self, movie_title):
        """ If movie title is available in a streaming service, returns a dictionary with three key-value pairs:
        the movie title, year, and service(s) available on. Otherwise, returns None. """

        # only return dictionary if movie title is found in catalog of streaming services
        services_list = []
        movie_year = None

        # iterate over list of streaming services
        for service_obj in self._list_services:
            # iterate over streaming service's catalog for if movie title is in it
            catalog = StreamingService.get_catalog(service_obj)

            for key in catalog:
                if movie_title is key:
                    movie_year = Movie.get_year(catalog[movie_title])
                    services_list.append(StreamingService.get_name(service_obj))

        if movie_year is None:
            return None

        else:
            return {'title': movie_title,
                    'year': movie_year,
                    'services': services_list}
