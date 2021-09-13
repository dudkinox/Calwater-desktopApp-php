package repository

import (
	"backend/model"
	"context"
)

type CrudRepositoryI interface {
	GetNameData(ctx context.Context) (crudResp model.GetNameResponse, err error)
}
