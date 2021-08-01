#include "JsonLib1.h"
#include "SQLiteDatabaseConnection.h"

FSQLiteDatabaseConnection Database = FSQLiteDatabaseConnection();

void UJsonLib1::DatabaseOpen()
{
	if (Database.Open(*GetPathDB(), nullptr, nullptr))
	{
		UE_LOG(LogTemp, Warning, TEXT("Database Open"));
	}
}

FString UJsonLib1::GetPathDB()
{
	return FPaths::ProjectDir() / "Database" / "db.db";
}

void UJsonLib1::CreateTableCities()
{
	FString CreateTableCities = "CREATE TABLE Cities (id INTEGER NOT NULL UNIQUE, NameCity TEXT, temp INTEGER, timestamp INTEGER);";
	if (Database.Execute(*CreateTableCities))
	{
		UE_LOG(LogTemp, Warning, TEXT("Create Cities table"));
	}
}

void UJsonLib1::CreateTableWeather()
{
	//TODO: Remove long strings
	FString CreateTableWeather = "CREATE TABLE Weather (temp INTEGER, feels_like INTEGER, temp_min INTEGER, temp_max INTEGER, pressure INTEGER, humidity INTEGER, NameCity TEXT, timestamp INTEGER, id INTEGER);";
	if (Database.Execute(*CreateTableWeather))
	{
		UE_LOG(LogTemp, Warning, TEXT("Create Weather table"));
	}
}

void UJsonLib1::InsertIntoCityTable(int IdCity, FString NameCity, int temp, int timestamp)
{
	//TODO: Remove long strings
	FString QueryInsert = FString::Printf(TEXT("INSERT INTO Cities (id, NameCity, temp, timestamp) VALUES (%i, \"%s\", %i, %i);"), 
												IdCity, *NameCity, temp, timestamp, IdCity);
	FString QueryUpdate = FString::Printf(TEXT("UPDATE Cities SET NameCity = \"%s\", temp = %i, timestamp = %i WHERE id = %i;"), 
												*NameCity, temp, timestamp, IdCity);
	if (Database.Execute(*QueryInsert))
	{
		UE_LOG(LogTemp, Warning, TEXT("Cities ONLOAD in BD"));
	}
	if(Database.Execute(*QueryUpdate))
	{
		UE_LOG(LogTemp, Warning, TEXT("Cities UPDATE in BD"));
	}
}

void UJsonLib1::InsertIntoWeatherTable(FWeatherMain WeatherData)
{
	FString Query = FString::Printf(TEXT("INSERT INTO Weather (temp, feels_like, temp_min, temp_max, pressure, humidity, NameCity, timestamp, id) VALUES (%i, %i, %i, %i, %i, %i, \"%s\", %i, %i);"), 
		WeatherData.temp, WeatherData.feels_like, WeatherData.temp_min, WeatherData.temp_max, WeatherData.pressure, WeatherData.humidity, *WeatherData.NameCity, WeatherData.timestamp, WeatherData.id);

	if (Database.Execute(*Query))
	{
		UE_LOG(LogTemp, Warning, TEXT("Weather onload in BD"));
	}
}

void UJsonLib1::GetSavedCitys(TArray<FWeatherMini>& SavedCitys)
{
	TArray<FWeatherMini> ArrSavedCitys;
	FSQLiteResultSet* Response = NULL;
	FString Query = "SELECT * FROM Cities;";
	if (Database.Execute(*Query, Response))
	{
		for (FSQLiteResultSet::TIterator Iterator(Response); Iterator; ++Iterator)
		{
			//TODO: Del variable
			int temp = Iterator->GetInt(TEXT("temp"));
			FString NameCity = Iterator->GetString(TEXT("NameCity"));
			int timestamp = Iterator->GetInt(TEXT("timestamp"));
			int id = Iterator->GetInt(TEXT("id"));

			FWeatherMini WeatherData = { id, NameCity, temp, timestamp };
			ArrSavedCitys.Add(WeatherData);
			SavedCitys = ArrSavedCitys;

		}
		UE_LOG(LogTemp, Warning, TEXT("SavedCitys onload"));
	}
}

void UJsonLib1::DeleteCityFromCitiesTable(int id)
{
	FString QueryDelete = FString::Printf(TEXT("DELETE FROM Cities WHERE id = %i;"), id);
	if (Database.Execute(*QueryDelete))
	{
		UE_LOG(LogTemp, Warning, TEXT("City id: %i DELETE from Cities table"), id);
	}
}

void UJsonLib1::DeleteWeathrsFromWeatherTable(int id)
{
	FString QueryDelete = FString::Printf(TEXT("DELETE FROM Weather WHERE id = %i;"), id);
	if (Database.Execute(*QueryDelete))
	{
		UE_LOG(LogTemp, Warning, TEXT("City id: %i DELETE history from Weather table"), id);
	}
}

void UJsonLib1::GetHistoryBySelectCity(int SelectedCityId, TArray<FWeatherMain>& History)
{
	TArray<FWeatherMain> Weather;
	FString QueryGetHistory = FString::Printf(TEXT("SELECT * FROM Weather WHERE id = %i;"), SelectedCityId);

	FSQLiteResultSet* Response = NULL;
	if (Database.Execute(*QueryGetHistory, Response))
	{
		for (FSQLiteResultSet::TIterator Iterator(Response); Iterator; ++Iterator)
		{
			FWeatherMain FullInfo = {
				Iterator->GetInt(TEXT("temp")),
				Iterator->GetInt(TEXT("feels_like")),
				Iterator->GetInt(TEXT("temp_min")),
				Iterator->GetInt(TEXT("temp_max")),
				Iterator->GetInt(TEXT("pressure")),
				Iterator->GetInt(TEXT("humidity")),
				Iterator->GetString(TEXT("NameCity")),
				Iterator->GetInt(TEXT("timestamp")),
				Iterator->GetInt(TEXT("id")),
			};
			Weather.Add(FullInfo);
		}
		UE_LOG(LogTemp, Warning, TEXT("Get history by selected city"));
	}
	
	History = Weather;
}

void UJsonLib1::DatabaseClose()
{
	Database.Close();
	UE_LOG(LogTemp, Warning, TEXT("Database Close"));
}