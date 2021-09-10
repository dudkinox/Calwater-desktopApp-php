package main

import (
	"backend/lib/db"
	"backend/model"
	"backend/repository"
	"backend/router"
	"backend/usecase"
	"fmt"
	"log"
	"net/http"
	"os"
	"strconv"

	"github.com/joho/godotenv"
	"github.com/labstack/echo/v4"
	"github.com/labstack/echo/v4/middleware"
)

func getConfig() model.EnvConfig {
	port, _ := strconv.Atoi(os.Getenv("PORT"))

	return model.EnvConfig{
		Host: os.Getenv("HOST_IP"),
		Port: port,
		Mongo: db.MongoConfig{
			Timeout:  5000,
			DBname:   os.Getenv("DATABASE_NAME"),
			Username: os.Getenv("DATABASE_USERNAME"),
			Password: os.Getenv("DATABASE_PASSWORD"),
			Host:     os.Getenv("DATABASE_HOST"),
			Port:     os.Getenv("DATABASE_PORT"),
		},
	}
}

func main() {
	godotenv.Load(".env")
	envConfig := getConfig()
	e := echo.New()
	e.Pre(middleware.CORSWithConfig(middleware.CORSConfig{
		AllowHeaders:     []string{"*"},
		AllowCredentials: true,
		AllowOrigins:     []string{"*"},
		AllowMethods:     []string{http.MethodGet, http.MethodHead, http.MethodPut, http.MethodPatch, http.MethodPost, http.MethodDelete},
	}))
	// Mongo
	mongo, err := db.Connect(envConfig.Mongo)
	if err != nil {
		log.Println(err)
		return
	}
	crudRepo := repository.NewCrudRepository(mongo)
	crudUseCase := usecase.NewCrudUseCase(&envConfig, crudRepo)
	router.Router(e, crudUseCase)
	e.Logger.Fatal(e.Start(fmt.Sprintf("%s%s%v", envConfig.Host, ":", envConfig.Port)))
}
