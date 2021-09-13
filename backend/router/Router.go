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
	e.GET("/test", call.GetHealthCheck)
}
