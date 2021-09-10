package controller

import (
	"backend/usecase"

	"github.com/labstack/echo/v4"
)

type CrudController struct {
	e       *echo.Echo
	usecase usecase.CrudUseCaseI
}

func NewCrudController(e *echo.Echo, usecase usecase.CrudUseCaseI) *CrudController {
	return &CrudController{
		e:       e,
		usecase: usecase,
	}
}

func (cc *CrudController) GetHealthCheck(ec echo.Context) error {
	return ec.String(200, "API มีระบบความปลอดภัยสูง")
}
