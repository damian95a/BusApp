# BusApp
This program is a study project. The requirement was to prepare the app in Polish.\
A purpose of the app is connecting to a database (set up locally) to show or insert data. The database consists of driver and bus data, bus stops, bus line (route), ride and their relationships.\

![image](https://user-images.githubusercontent.com/79938517/217394432-02a55b3c-4998-4f6d-b48f-b50cffd3cf74.png)

The app has really simple signing in. Any user can see simple info about any bus and check a timetable or routes between 2 stops. User logged in as a driver can obtain all information from any table. If you sign in to admin account you can additionally insert a new record to any table. The database checks if data are valid (driver/bus can have only one ride at the same time or there cannot be a bus stop twice) and raises exception (showing an error dialogue window) otherwise.\

<p align=center>
<img src=https://user-images.githubusercontent.com/79938517/217394577-8ef55d9c-627e-464c-ac3b-3da0525ad85e.png><BR>
<img src=https://user-images.githubusercontent.com/79938517/217394748-5808b4fb-3218-4d74-bc48-a8f7497af4ca.png><BR>
<img src=https://user-images.githubusercontent.com/79938517/217394776-377a86e3-b614-45ba-9f28-18c51c0cf7de.png>
</p>
The program was tested with Linux os and uses wxWidgets and libpqxx.
