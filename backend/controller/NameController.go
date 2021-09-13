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
	// 200 ปกติ
	// 400 การเขียนโค้ดบัค หรือ error
	// 500 server พัง หรือว่า เซิฟล่ม
	return ec.String(200, "<h1>API มีระบบความปลอดภัยสูงมาก</h1>")
}
