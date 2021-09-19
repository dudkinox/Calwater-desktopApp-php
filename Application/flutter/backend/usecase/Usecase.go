package usecase

import (
	"backend/model"
	"context"
)

type CrudUseCaseI interface {
	GetHealthCheck(ctx context.Context) (err error)
	InfoUC(ctx context.Context) (ModelSave model.GetInfoResponse, err error)
	InsertInfoUC(ctx context.Context, ModelSave model.ModelInfo) (ID string, err error)
	DeleteInfoUC(ctx context.Context, ID string) (Status string, err error)
}
