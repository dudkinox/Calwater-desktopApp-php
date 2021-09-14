package router

import (
	"backend/controller"
	"backend/usecase"

	"github.com/labstack/echo/v4"
)

func Router(e *echo.Echo, crudUseCase usecase.CrudUseCaseI) {
	call := controller.NewCrudController(e, crudUseCase)

	e.GET("", call.GetHealthCheck)
	api := e.Group("api/info")
	api.GET("", call.Info)
	api.POST("", call.InsertInfo)
	api.DELETE("/:id", call.DeleteInfo)
}
