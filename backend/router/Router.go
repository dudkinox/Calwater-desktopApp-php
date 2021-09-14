package router

import (
	"backend/controller"
	"backend/usecase"

	"github.com/labstack/echo/v4"
)

func Router(e *echo.Echo, crudUseCase usecase.CrudUseCaseI) {
	call := controller.NewCrudController(e, crudUseCase)

	// localhost:1412
	e.GET("", call.GetHealthCheck)
	api := e.Group("api")
	// localhost:1412/api/get_name
	api.GET("/get_name", call.GetName)
	// localhost:1412/api/info
	api.GET("/info", call.Info)
}
