package controller

import (
	"backend/model"
	"backend/usecase"
	"context"
	"encoding/json"
	"fmt"

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
	Total_Cr := 110.3
	Cu := 54.43
	Mn := 2.239
	Ni := 44.94
	Pb := 0.001
	Zn := 201.2
	Total_Metal := (Total_Cr / (1000 * 51.996)) + (Cu / (1000 * 63.55)) + (Mn / (1000 * 54.93)) + (Ni / (1000 * 58.93)) + (Pb / (1000 * 207.2)) + (Zn / (1000 * 65.4))
	fmt.Println("Total_Metal =>", Total_Metal)
	// var Ca_OH_2 = (((Total_Cr / (1000 * 51.996)) * (3 / 2) * 74.093) + (((Cu / (1000 * 63.55)) + (Mn / (1000 * 54.93)) + (Ni / (1000 * 58.93)) + (Pb / (1000 * 207.2)) + (Zn / (1000 * 65.4))) * 74.093)) * (100 / 93.15)
	Ca_OH_2 := (((Total_Cr / (1000 * 51.996)) * (3 / 2) * 74.093) + (((Cu / (1000 * 63.55)) + (Mn / (1000 * 54.93)) + (Ni / (1000 * 58.93)) + (Pb / (1000 * 207.2)) + (Zn / (1000 * 65.4))) * 74.093)) * (100 / 93.15)
	fmt.Println("Ca_OH_2 =>", Ca_OH_2)
	var Model1L = Ca_OH_2 * 14.659
	fmt.Println("Model1L =>", Model1L)
	var Lab1L = Ca_OH_2 * 14.67
	fmt.Println("Lab1L =>", Lab1L)
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
