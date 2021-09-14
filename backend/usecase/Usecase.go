package usecase

import (
	"backend/model"
	"context"
)

type CrudUseCaseI interface {
	GetHealthCheck(ctx context.Context) (err error)
	GetNameUC(ctx context.Context) (ModelSave model.GetNameResponse, err error)
	InfoUC(ctx context.Context) (ModelSave model.GetInfoResponse, err error)
}
