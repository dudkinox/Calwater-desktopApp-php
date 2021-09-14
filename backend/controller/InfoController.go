package controller

import (
	"backend/model"
	"backend/usecase"
	"context"
	"encoding/json"

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
	return ec.String(200, "สวัสดี อันนี้ทดสอบเฉยๆ")
}

func (cc *CrudController) Info(ec echo.Context) error {

	result, err := cc.usecase.InfoUC(context.Background())
	if err != nil {
		return ec.JSON(400, err)
	}

	return ec.JSON(200, result)
}

func (cc *CrudController) InsertInfo(ec echo.Context) error {

	var req model.ModelInfo
	err := json.NewDecoder(ec.Request().Body).Decode(&req)
	if err != nil {
		return err
	}

	ID, error := cc.usecase.InsertInfoUC(context.Background(), req)

	if error != nil {
		return error
	}

	return ec.JSON(200, ID)
}

func (cc *CrudController) DeleteInfo(ec echo.Context) error {

	var id = ec.Param("id")

	Status, error := cc.usecase.DeleteInfoUC(context.Background(), id)

	if error != nil {
		return error
	}

	return ec.JSON(200, Status)
}
